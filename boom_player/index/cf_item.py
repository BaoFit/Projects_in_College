#基于物品的协同过滤实现
import math
import numpy as np


def transformdata(data):
    '''
    将矩阵转置
    '''
    newdata = {}
    for user in data:
        for song in data[user]:
            #初始化
            newdata.setdefault(song,{})
            #物品与用户对调
            newdata[song][user] = data[user][song]  #字典可以直接写[key]，就表示插入key值了。非常简便
    return newdata


def sim_distance(data,song1,song2):
    #欧氏距离求相似度，距离越大，越相似
    commonusers = [user for user in data[song1] if user in data[song2]]
    if len(commonusers) == 0: return 0
    # 平方和
    sumSq = np.sum([math.pow(data[song1][user] - data[song2][user], 2) for user in commonusers])
    # 使最终结果是，越相似，距离越大。所以将上面距离取倒数即可
    sim = 1 / (1 + math.sqrt(sumSq))
    return sim

'''
def sim_pearson(data, song1, song2):
    #皮尔逊计算相似度
    # 计算pearson系数，先要收集两个用户公共歌曲名单
    commonsongs = [ song for song in data[song1] if song in data[song2]]
    n = float(len(commonsongs))
    if n == 0:
        return 0
    # 分别对两个用户的公共歌曲song分数总和
    sum1 = np.sum([data[song1][song] for song in commonsongs])
    sum2 = np.sum([data[song2][song] for song in commonsongs])
    # 计算乘积之和
    sum12 = np.sum([data[song1][song] * data[song2][song] for song in commonsongs])
    # 计算平方和
    sum1Sq = np.sum([math.pow(data[song1][song], 2) for song in commonsongs])
    sum2Sq = np.sum([math.pow(data[song2][song], 2) for song in commonsongs])
    # 计算分子
    num = sum12 - sum1 * sum2 / n
    # 分母
    den = math.sqrt((sum1Sq - math.pow(sum1, 2) / n) * (sum2Sq - math.pow(sum2, 2) / n))
    if den == 0:  return 0
    return num / den
'''

def topmatches(data, givensong, simscore):
    '''
    歌曲匹配推荐：给定一首歌曲，返回其他歌曲相似度排名
    '''
    # 建立最终结果列表
    usersscores = [(simscore(data, givensong, other), other) for other in data if other != givensong]
    # 对列表排序
    usersscores.sort(key=None, reverse=True)
    return usersscores
#求所有歌曲的相似度
def calSimilarItems(data):
#以物品为中心，对偏好矩阵转置
    songdata = transformdata(data)
    ItemAllMatches = {}
    for song in songdata:
         ItemAllMatches.setdefault(song,[])
         #对每个电影 都求它的匹配电影集,求电影之间的距离用欧式距离
         ItemAllMatches[song] = topmatches(songdata, song,sim_distance)
    return ItemAllMatches



def getrecommendations(data, targetuser, songsAllsimilarity):
    '''
    输入songAllSimilarity就是上面calsimilarItems已经计算好的所有物品之间的相似度数据集：
     '''
    # 获得所有物品之间的相似数据集
    scoresum = {}
    simsum = {}
    # 遍历所有看过的电影
    for watchedsong in data[targetuser]:
        rating = data[targetuser][watchedsong]
        # 遍历与当前电影相近的电影
        for (similarity, newsong) in songsAllsimilarity[watchedsong]:  # 取一对元组
            # 已经对当前物品评价过，则忽略
            if newsong in data[targetuser]: continue
            scoresum.setdefault(newsong, 0)
            simsum.setdefault(newsong, 0)
            # 全部相似度求和
            simsum[newsong] += similarity
            # 评价值与相似度加权之和
            scoresum[newsong] += rating * similarity

    rankings = [(score / simsum[newsong], newsong) for newsong, score in scoresum.items()]
    rankings.sort(key=None, reverse=True)
    return rankings

